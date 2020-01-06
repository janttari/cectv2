#!/bin/bash
#lähetetään exit-signaali cectv:n komentotiedostoon
konffifile="/etc/cectv.json"
commandfile=$(cat $konffifile |grep commandfile|awk -F\" 'NF>1 { print $(NF-1) }')
echo "exit"> $commandfile

