# TensorRT-SMOKE

## Steps
```
# 1.Install TensorRT
# 下载TAR包: https://developer.nvidia.cn/nvidia-tensorrt-8x-download
tar -xvzf TensorRT-8.0.3.4.Linux.x86_64-gnu.cuda-10.2.cudnn8.2.tar.gz
# export TENSORRT_DIR=~/TensorRT-8.0.3.4
# 编译包含插件的TensorRT OSS
git clone -b release/8.0 https://github.com/Yibin122/TensorRT.git
cd TensorRT/
git submodule update --init --recursive
mkdir -p build && cd build
cmake .. -DTRT_LIB_DIR=~/TensorRT-8.0.3.4/lib -DTRT_OUT_DIR=`pwd`/out -DCUDA_VERSION=10.2
make -j$(nproc)
make install

# 2.Generate ONNX
# 在MMDetection3d环境下导出
pip install torch==1.8.0 torchvision==0.9.0
pip install mmdet==2.19.0
pip install mmsegmentation==0.20.0
git clone https://github.com/Yibin122/mmdetection3d.git
cd mmdetection3d/
pip install -v -e .
python smoke_to_onnx.py  # smoke.onnx

# 3.Generate engine
# 在MMDeploy环境下部署
git clone https://github.com/open-mmlab/mmdeploy.git
cd mmdeploy/
git submodule update --init --recursive
pip install mmcv-full==1.4.0 -f https://download.openmmlab.com/mmcv/dist/cu102/torch1.8.0/index.html
pip install -e .
mkdir -p build && cd build
cmake -DMMDEPLOY_TARGET_BACKENDS=trt -DTENSORRT_DIR=~/TensorRT-8.0.3.4 ..
make -j$(nproc)
python onnx_to_tensorrt.py  # smoke.trt8

# 4.Run engine
git clone https://github.com/Yibin122/TensorRT-SMOKE.git
cd TensorRT-SMOKE/
mkdir build && cd build
cmake ..
make
./smoke_trt
```

## TODO
- [ ] MonoFlex
