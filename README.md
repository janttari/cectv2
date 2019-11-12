# cectv

IPTV player frontend for Raspberry using HDMI CEC

![](https://raw.githubusercontent.com/janttari/cectv2/master/cectv2.png)

Install or update:

    wget https://github.com/janttari/cectv2/blob/master/cectv2.deb && sudo dpkg -i cectv2.deb

edit files in 
- /opt/cectv2/channels.conf
- /opt/cectv2/channels/

start cectv2:

    sudo systemctl start cectv2

autostart cectv2:

    sudo systemctl enable cectv2


