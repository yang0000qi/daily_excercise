#include "params.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#undef SERR
#define SERR(fmt, args...) \
            printf("Camera[ERROR][SENSOR] %s: %d: " fmt"\n", __func__, __LINE__, ##args);


#define XML_GET_INT_ATTR(_var_, _node_, _attr_, _opt_, type, _default_) \
{ \
    xmlChar* _p_ = xmlGetProp(_node_, (const xmlChar *)_attr_); \
    if (_p_) { \
        _var_ = (type)atoi((const char *)_p_); \
        xmlFree(_p_); \
    } else if (_opt_) {\
        _var_ = (type)_default_; \
    } else  { \
        SERR("could not get attribute " _attr_); \
        return -1; \
    } \
}

static int parse_input_element (xmlDocPtr doc, xmlNodePtr parent)
{
    xmlNodePtr cur = parent->xmlChildrenNode;
    int rc = 0, type = 0;

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"camera_0v10640"))) {
            XML_GET_INT_ATTR(type, cur, "enable", 1, int, 0);
            if(type)
                rc = SENSOR_CAMERA_OV10640;
        }
        else if ((!xmlStrcmp(cur->name, (const xmlChar *)"camera_0v10635"))) {
            XML_GET_INT_ATTR(type, cur, "enable", 1, int, 0);
            if(type)
                rc = SENSOR_CAMERA_OV10635;
        }
        else if ((!xmlStrcmp(cur->name, (const xmlChar *)"camera_ar0143at"))) {
            XML_GET_INT_ATTR(type, cur, "enable", 1, int, 0);
            if(type)
                rc = SENSOR_CAMERA_AR0143AT;
        }
        
        cur = cur->next;
    }

    return rc;
}

int parse_xml_config_camera_type(const char* filename)
{
    int rc = 0;

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(filename);

    if (doc == NULL )
    {
        SERR("Document not parsed successfully");
        return -1;
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL)
    {
        SERR("Empty config file");
        xmlFreeDoc(doc);
        return -1;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "camera_type"))
    {
        SERR("Wrong config file format, root node != qcarcam_inputs");
        xmlFreeDoc(doc);
        return -1;
    }

    rc = parse_input_element(doc, cur);

    xmlFreeDoc(doc);

    return rc;
}

