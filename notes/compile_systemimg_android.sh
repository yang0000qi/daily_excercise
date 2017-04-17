#!/bin/bash

1. Makefile -> /build/core/main.mk -> /build/core/Makefile 
    :build_image.py

2./build/tools/releasetools/build_image.py
    build_command = ["mkuserimg.sh"]

3.mkuserimg.sh
    MAKE_EXT4FS_CMD="make_ext4fs $ENABLE_SPARSE_IMAGE $FCOPT -l $SIZE -a $MOUNT_POINT $OUTPUT_FILE $SRC_DIR"

notes:
    1.make_ext4fs parameter -J can choose journal function,add -J can reduce storage space. [-J journal-options]
    2.imx6/BoardConfigCommon.mk/BOARD_SYSTEMIMAGE_PARTITION_SIZE can adjust system.img size
