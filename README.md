# Marshall-Hand
Code for a hand 

https://z.umn.edu/M_H

<!-- ```bash
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
   ``` -->


## Manual Installation(Not Recommended, unless you want to learn or your Jetson Nano 2gb is brand new)

### [Write Image (Jetson Nano 2gb)](jetson-nano-2gb-jp461-sd-card-image.zip) to SD Card using [balenaEtcher](https://etcher.balena.io/)


### Pull the docker image 'nvcr.io/nvidia/l4t-ml:r32.7.1-py3' 
```bash
sudo docker pull nvcr.io/nvidia/l4t-ml:r32.7.1-py3
```

### Create a folder to store data
```bash
mkdir ~/l4t-data
```

### Plug in Logitech C270 Webcam & list USB devices to verify it is detected
```bash
lsusb
```

### Run the docker image 'nvcr.io/nvidia/l4t-ml:r32.7.1-py3' 
```bash
sudo docker run --runtime nvidia -it --network host --volume ~/l4t-data --device /dev/video0 nvcr.io/nvidia/l4t-ml:r32.7.1-py3
```



After Jupyter Notebook is running, open a terminal and run the following commands:


### Install torch2trt 

   #### Clone torch2trt Repo to quick install pre-recs
   ```bash
   git clone https://github.com/NVIDIA-AI-IOT/torch2trt
   ```

   #### Go into torch2trt folder
   ```bash
   cd torch2trt
   ```

   #### Install torch2trt Pre-recs (takes a while)
   ```bash
   python3 setup.py install --plugins
   ```

   #### Install miscellaneous packages
   ```bash
   pip3 install tqdm cython pycocotools
   ```

   #### Install MathPlotLib
   ```bash
   apt-get install python3-matplotlib
   ```

   #### go back to root
   ```bash
   cd /
   ```

   <br>

### Install trt_pose

   #### Clone trt_pose Repo to quick install pre-recs
   ```bash
   git clone https://github.com/NVIDIA-AI-IOT/trt_pose
   ```

   #### Go into trt_pose folder
   ```bash
   cd trt_pose
   ```

   #### Install trt_pose Pre-recs (takes a while)
   ```bash
   python3 setup.py install
   ```

   #### Go back to root
   ```bash
   cd /
   ```

   <br>

### Install jetcam 

   #### Clone Jetcam Repo to quick install pre-recs
   ```bash
   git clone https://github.com/NVIDIA-AI-IOT/jetcam
   ```

   #### Go into jetcam folder
   ```bash
   cd jetcam
   ```

   #### Install jetcam Pre-recs (takes a while)
   ```bash
   python3 setup.py install
   ```

   #### Go back to root
   ```bash
   cd /
   ```

   <br>


### Install trt_pose_hand

   #### Clone trt_pose_hand Repo to quick install pre-recs
   ```bash
   git clone https://github.com/NVIDIA-AI-IOT/trt_pose_hand.git
   ```


   #### Go into trt_pose_hand folder
   ```bash
   cd trt_pose_hand
   ```

   #### Install scikit-learn
   ```bash
   pip3 install scikit-learn
   ```

   


## Start Docker Container 

### Normal Launch 

   ```bash
sudo docker run --name handV7 --runtime nvidia -it \
    -e DISPLAY=$DISPLAY \
    --network host \
    -v ~/l4t-data:/l4t-data \
    --device /dev/video* \
    --device /dev/ttyUSB* \
    --workdir /trt_hand_pose \
    felipegalind0/trt_hand_pose:v7\
    python3 gesture_classification_print.py
```

### No Serial (remove '--device /dev/ttyUSB0 \')

   ```bash
sudo docker run --name handV7 --runtime nvidia -it \
    -e DISPLAY=$DISPLAY \
    --network host \
    -v ~/l4t-data:/l4t-data \
    --device /dev/video0 \
    --workdir /trt_hand_pose \
    felipegalind0/trt_hand_pose:v7 \
    python3 gesture_classification_print.py
```

### JupyterLab Launch (remove 'python3 gesture_classification_print.py')

   ```bash
sudo docker run --name handV7 --runtime nvidia -it \
    -e DISPLAY=$DISPLAY \
    --network host \
    -v ~/l4t-data:/l4t-data \
    --device /dev/video0 \
    --workdir /trt_hand_pose \
    felipegalind0/trt_hand_pose:v7 \
```

### enable xhost
```bash
xhost +local:docker
```
