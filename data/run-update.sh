#!/bin/sh
# To indicate a step description, prefix the text with "NOTE: "
# To indicate a progress hint (from 0 to 19), echo "PROGRESS: <progress>"

echo "PROGRESS: 0"

CACHE_DIR=/var/lib/system-update/packages
OPKG_FLAGS=""

if [ ! -d ${CACHE_DIR} ] ; then
	echo "NOTE: No updates available. Rebooting now"
        reboot
fi

echo "NOTE: Starting system update"

NUM_PACKAGES=`ls -alh ${CACHE_DIR} | wc -l`
echo "PROGRESS: 2"

echo "NOTE: Installing ${NUM_PACKAGES} packages"

echo "PROGRESS: 8"

opkg $OPKG_FLAGS --cache=${CACHE_DIR} upgrade

echo "NOTE: All packages are installed now"
echo "PROGRESS: 16"

echo "NOTE: Cleaning up"

rm -rf ${CACHE_DIR}
rm -f /system-update
echo "PROGRESS: 18"

echo "NOTE: Rebooting system"
echo "PROGRESS: 19"

reboot
