# Marshall-Hand
Code for a hand 



```bash
sudo vim /etc/systemd/system/docker-l4t-ml.service
```
Paste this text 
```
[Unit]
Description=Autostart l4t-ml Docker container
Requires=docker.service
After=docker.service

[Service]
Restart=on-failure
ExecStart=/usr/bin/docker run --runtime nvidia --name l4t-ml-container --network host --volume /home/felg/l4t-data --device /dev/video0 nvcr.io/nvidia/l4t-ml:r32.7.1-py3
ExecStop=/usr/bin/docker stop l4t-ml-container

[Install]
WantedBy=multi-user.target


```
Then press ESC

then type ':wq'





1. Reload `systemd`:
   
   ```bash
   sudo systemctl daemon-reload
   ```

2. Enable the service to start on boot:
   
   ```bash
   sudo systemctl enable docker-l4t-ml.service
   ```

3. Optionally, start the service immediately without rebooting:
   
   ```bash
   sudo systemctl start docker-l4t-ml.service
   ```

4. Check the service status to ensure it's running properly:
   
   ```bash
   sudo systemctl status docker-l4t-ml.service
   ```








After Jupyter Notebook is running, open a terminal and run the following commands:

   Clone NVIDIA AI IOT Github Repo to quick install pre-recs
   ```bash
   git clone https://github.com/NVIDIA-AI-IOT/torch2trt
   ```

   go into torch2trt folder
   ```bash
   cd torch2trt
   ```

   Install Pre-recs
   ```bash
   python3 setup.py install --plugins
   ```

   Install miscellaneous packages

   ```bash
   pip3 install tqdm cython pycocotools
   ```

   Install MathPlotLib

   ```bash
   apt-get install python3-matplotlib
   ```

   ```bash
   git clone https://github.com/NVIDIA-AI-IOT/trt_pose
   ```

   cd trt_pose

   python3 setup.py install




   ```bash
sudo docker run --name handV5 --runtime nvidia -it \
    -e DISPLAY=$DISPLAY \
    --network host \
    -v ~/l4t-data:/l4t-data \
    --device /dev/video0 \
    --device /dev/ttyUSB0 \
    --workdir /trt_hand_pose \
    felipegalind0/trt_hand_pose:v5 \
    python3 gesture_classification_print.py


```
