# Marshall-Hand
Code for a hand 


[Unit]
Description=Autostart l4t-ml Docker container
Requires=docker.service
After=docker.service

[Service]
Restart=always
ExecStart=/usr/bin/docker run --runtime nvidia -it --rm --network host --volume ~/l4t-data --device /dev/video0 nvcr.io/nvidia/l4t-ml:r32.7.1-py3
ExecStop=/usr/bin/docker stop l4t-ml

[Install]
WantedBy=multi-user.target
