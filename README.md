# Parallel implementation of Canny Edge detector 
CUDA implementation of Canny edge detection algorithm

## Platform Requirement
Ubuntu 18.04, g++ v7.5, CUDA v9.1, Nvidia Quadro P5000 GPU

## Compile and Run
### serial CPU  
`make serial` 
`./bin/serial`
### parallel CUDA GPU 
`make cuda`
`nvprof ./parallel_cuda`
## Dependencies
CUDA, OpenCV

# Installing the NVIDIA driver, CUDA and cuDNN on Linux (Ubuntu 20.04)

This is a companion piece to my instructions on building [TensorFlow from source](https://gist.github.com/kmhofmann/e368a2ebba05f807fa1a90b3bf9a1e03).
In particular, the aim is to install the following pieces of software

- [NVIDIA graphics card driver](https://www.nvidia.com/en-us/drivers/unix/) (v450.57)
- [CUDA](https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=2004&target_type=runfilelocal) (v11.0.2)
- [cuDNN](https://developer.nvidia.com/cudnn) (v8.0.2.39)

on an Ubuntu Linux system, in particular Ubuntu 20.04.

At the time of writing (**2020-08-06**), these were the latest available versions. As a disclaimer, please note that I am **not** interested in running an outdated Ubuntu version or installing a CUDA/cuDNN version that is not the latest. Therefore, **the below instructions may or may not be useful to you**. Please also note that the instructions **are likely outdated**, since I only update them occasionally. **Don't just copy these instructions, but check what the respective latest versions are and use these instead!**

### Installing the NVIDIA driver
Download and install the latest NVIDIA graphics driver from here: https://www.nvidia.com/en-us/drivers/unix/. Note that every CUDA version requires a minimum version of the driver; check this beforehand.

Ubuntu 20.04 currently offers installation of the NVIDIA driver version 440.100 through its built-in 'Additional Drivers' mechanism, which should be sufficient for CUDA 10.2. CUDA 11.0 appears to require a newer version of the NVIDIA driver, so we're going to install this manually.

Download and install the latest NVIDIA graphics driver from here: https://www.nvidia.com/en-us/drivers/unix/.

    sudo sh NVIDIA-Linux-x86_64-450.57.run

The CUDA runfile also includes a version of the NVIDIA graphics driver, but I like to separate installing either, as the version supplied with CUDA Is not necessarily the latest version of the driver.

### Installing CUDA
Download the latest CUDA version [here](https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=2004&target_type=runfilelocal). For example, I downloaded:

    $ wget http://developer.download.nvidia.com/compute/cuda/11.0.2/local_installers/cuda_11.0.2_450.51.05_linux.run

      
Thankfully, CUDA 11 currently supports the up-to-date Ubuntu version, 20.04, so we don't need to jump through hoops to deal with an `unsupported GNU version` error as in [previous versions](https://gist.github.com/kmhofmann/cee7c0053da8cc09d62d74a6a4c1c5e4) of this document. Simply install as per the official instructions:

    $ sudo sh cuda_11.0.2_450.51.05_linux.run

You may need to confirm that the display driver is already installed, and de-select installation of the display driver.

Once finished, you should see a summary like this:

	===========
	= Summary =
	===========

	Driver:   Not Selected
	Toolkit:  Installed in /usr/local/cuda-11.0/
	Samples:  Installed in /home/michael/, but missing recommended libraries

	Please make sure that
	 -   PATH includes /usr/local/cuda-11.0/bin
	 -   LD_LIBRARY_PATH includes /usr/local/cuda-11.0/lib64, or, add /usr/local/cuda-11.0/lib64 to /etc/ld.so.conf and run ldconfig as root

	To uninstall the CUDA Toolkit, run cuda-uninstaller in /usr/local/cuda-11.0/bin

	Please see CUDA_Installation_Guide_Linux.pdf in /usr/local/cuda-11.0/doc/pdf for detailed information on setting up CUDA.
	***WARNING: Incomplete installation! This installation did not install the CUDA Driver. A driver of version at least .00 is required for CUDA 11.0 functionality to work.
	To install the driver using this installer, run the following command, replacing <CudaInstaller> with the name of this run file:
	    sudo <CudaInstaller>.run --silent --driver

Do what the instructions given in the summary say and add the given directories to your `PATH` and `LD_LIBRARY_PATH`. For example by adding the following lines to your `.bashrc`, `.zshrc`, or whatever shell you are using:

    export PATH=/usr/local/cuda-11.0/bin:$PATH
    export LD_LIBRARY_PATH=/usr/local/cuda-11.0/lib64:$LD_LIBRARY_PATH

### Installing cuDNN

Just go [here](https://developer.nvidia.com/cudnn) and follow the [instructions](https://docs.nvidia.com/deeplearning/sdk/cudnn-install/index.html). You'll have to log in, so downloading of the right cuDNN binary packages cannot be easily automated. Meh.

Once downloaded, un-tar the file and copy the contents to their respective locations:

    $ tar -xzvf cudnn-11.0-linux-x64-v8.0.2.39.tgz
    
    $ sudo cp cuda/include/cudnn*.h /usr/local/cuda/include
    $ sudo cp cuda/lib64/libcudnn* /usr/local/cuda/lib64
    $ sudo chmod a+r /usr/local/cuda/include/cudnn*.h /usr/local/cuda/lib64/libcudnn*
    
    
    
# Installing OpenCV on Linux 

## Getting OpenCV Source Code
cd ~/<my_working_directory>
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

1.Create a temporary directory, which we denote as <cmake_build_dir>, where you want to put the generated Makefiles, project files as well the object files and output binaries and enter there.

For example

`cd ~/opencv
mkdir build
cd build`

2 Configuring. Run cmake [<some optional parameters>] <path to the OpenCV source directory>

`cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..`

3.
Description of some parameters
build type: CMAKE_BUILD_TYPE=Release\Debug
to build with modules from opencv_contrib set OPENCV_EXTRA_MODULES_PATH to <path to opencv_contrib/modules/>
set BUILD_DOCS for building documents
set BUILD_EXAMPLES to build all examples

4. [optional] Building python. Set the following python parameters:
PYTHON2(3)_EXECUTABLE = <path to python>
PYTHON_INCLUDE_DIR = /usr/include/python<version>
PYTHON_INCLUDE_DIR2 = /usr/include/x86_64-linux-gnu/python<version>
PYTHON_LIBRARY = /usr/lib/x86_64-linux-gnu/libpython<version>.so
PYTHON2(3)_NUMPY_INCLUDE_DIRS = /usr/lib/python<version>/dist-packages/numpy/core/include/

5. [optional] Building java.
Unset parameter: BUILD_SHARED_LIBS
It is useful also to unset BUILD_EXAMPLES, BUILD_TESTS, BUILD_PERF_TESTS - as they all will be statically linked with OpenCV and can take a lot of memory.

6. Build. From build directory execute make, it is recommended to do this in several threads
For example

`make -j7 # runs 7 jobs in parallel`
7. [optional] Building documents. Enter <cmake_build_dir/doc/> and run make with target "doxygen"

For example

`cd ~/opencv/build/doc/
make -j7 doxygen`

8. To install libraries, execute the following command from build directory
sudo make install
9. [optional] Running tests

Get the required test data from OpenCV extra repository.
For example

`git clone https://github.com/opencv/opencv_extra.git`
set OPENCV_TEST_DATA_PATH environment variable to <path to opencv_extra/testdata>.
execute tests from build directory.
For example

`<cmake_build_dir>/bin/opencv_test_core`
