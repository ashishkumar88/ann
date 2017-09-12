cc_binary(
    name = "ann",
    srcs = ["ann.cc"],
    linkopts = 
		["-lopencv_core", "-lopencv_imgproc", "-lopencv_highgui", "-lopencv_imgcodecs",  
        "-lopencv_objdetect", "-lopencv_videoio", "-lopencv_cudaobjdetect", "-lopencv_cudaimgproc", "-lopencv_cudawarping",
		"-Wl,--version-script=tensorflow/tf_version_script.lds"],
    deps = [
        "//tensorflow/cc:cc_ops",
        "//tensorflow/cc:client_session",
        "//tensorflow/core:tensorflow",
    ],
)
