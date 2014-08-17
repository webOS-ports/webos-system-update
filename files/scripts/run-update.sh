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

opkg $OPKG_FLAGS -o / --cache=${CACHE_DIR} upgrade

echo "NOTE: All packages are installed now"
echo "PROGRESS: 16"

echo "NOTE: Cleaning up"

rm -rf ${CACHE_DIR}
rm -f /system-update
echo "PROGRESS: 18"

# Enable opkg configure job for next boot as we didn't performed
# any post installation steps
systemctl enable opkg-configure

# If we're forced to update to a specific verison update the current-version file
if [ -e /var/preferences/system-update/update-to-version ] ; then
    cat /var/preferences/system-update/update-to-version > /var/preferences/system-update/current-version
fi

echo "NOTE: Rebooting system"
echo "PROGRESS: 19"

reboot
