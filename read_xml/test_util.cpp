/* ===========================================================================
 * Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================== */
#include "test_util.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define XML_GET_INT_ATTR(_var_, _node_, _attr_, _opt_, type, _default_) \
{ \
    xmlChar* _p_ = xmlGetProp(_node_, (const xmlChar *)_attr_); \
    if (_p_) { \
        _var_ = (type)atoi((const char *)_p_); \
        xmlFree(_p_); \
    } else if (_opt_) {\
        _var_ = (type)_default_; \
    } else  { \
        QCARCAM_ERRORMSG("could not get attribute " _attr_); \
        return -1; \
    } \
}

#define XML_GET_FLOAT_ATTR(_var_, _node_, _attr_, _opt_, _default_) \
{ \
    xmlChar* _p_ = xmlGetProp(_node_, (const xmlChar *)_attr_); \
    if (_p_) { \
        _var_ = atof((const char *)_p_); \
        xmlFree(_p_); \
    } else if (_opt_) {\
        _var_ = _default_; \
    } else  { \
        QCARCAM_ERRORMSG("could not get attribute " _attr_); \
        return -1; \
    } \
}

static int parse_input_element (xmlDocPtr doc, xmlNodePtr parent, test_util_xml_input_t* input)
{
    xmlNodePtr cur = parent->xmlChildrenNode;

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"properties"))) {
            XML_GET_INT_ATTR(input->qcarcam_input_id, cur, "input_id", 0, qcarcam_input_desc_t, 0);
            XML_GET_INT_ATTR(input->use_event_callback, cur, "event_callback", 1, int, 1);
            XML_GET_INT_ATTR(input->frame_timeout, cur, "frame_timeout", 1, int, -1);
        }
        else if ((!xmlStrcmp(cur->name, (const xmlChar *)"display_setting")))
        {
            XML_GET_INT_ATTR(input->window_params.display_id, cur, "display_id", 0, int, 0);
            XML_GET_INT_ATTR(input->n_buffers_display, cur, "disp_nbufs", 1, int, 3);
            XML_GET_FLOAT_ATTR(input->window_params.window_size[0], cur, "window_width", 1, 1.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_size[1], cur, "window_height", 1, 1.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_pos[0], cur, "window_pos_x", 1, 0.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_pos[1], cur, "window_pos_y", 1, 0.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_source_size[0], cur, "src_width", 1, 1.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_source_size[1], cur, "src_height", 1, 1.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_source_pos[0], cur, "src_x", 1, 0.0f);
            XML_GET_FLOAT_ATTR(input->window_params.window_source_pos[1], cur, "src_y", 1, 0.0f);
            XML_GET_INT_ATTR(input->window_params.zorder, cur, "zorder", 1, int, -1);
            XML_GET_INT_ATTR(input->window_params.pipeline_id, cur, "pipeline", 1, int, -1);
        }
        else if ((!xmlStrcmp(cur->name, (const xmlChar *)"buffer_setting")))
        {
            XML_GET_INT_ATTR(input->n_buffers_qcarcam, cur, "nbufs", 1, int, 3);
            XML_GET_INT_ATTR(input->format, cur, "format", 0, int, 0);
            XML_GET_INT_ATTR(input->buffer_size[0], cur, "bufsize_width", 0, int, 0);
            XML_GET_INT_ATTR(input->buffer_size[1], cur, "bufsize_height", 0, int, 0);
        }
        cur = cur->next;
    }

    return 0;
}

int parse_xml_config_file(const char* filename, test_util_xml_input_t* xml_inputs, unsigned int max_num_inputs)
{
    int rc = 0, numInputs = 0;

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(filename);

    if (doc == NULL )
    {
        QCARCAM_ERRORMSG("Document not parsed successfully");
        return -1;
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL)
    {
        QCARCAM_ERRORMSG("Empty config file");
        xmlFreeDoc(doc);
        return -1;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "qcarcam_inputs"))
    {
        QCARCAM_ERRORMSG("Wrong config file format, root node != qcarcam_inputs");
        xmlFreeDoc(doc);
        return -1;
    }

    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"input_device")))
        {
            rc = parse_input_element(doc, cur, &xml_inputs[numInputs]);
            if (!rc)
            {
                numInputs++;
            }
            else
            {
                QCARCAM_ERRORMSG("Missing parameter in config file");
            }
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);

    return numInputs;
}
