cc_binary(
    name = "ann",
    srcs = ["ann.cpp"],
    linkopts = 
		["-lopencv_core", "-lopencv_imgproc", "-lopencv_highgui", "-lopencv_imgcodecs",  
        "-lopencv_objdetect", "-lopencv_videoio", "-lopencv_cudaobjdetect", "-lopencv_cudaimgproc", "-lopencv_cudawarping",
		"-Wl,--version-script=tensorflow/tf_version_script.lds"],
    deps = [":network"],
)

cc_library(
    name = "neuron",
    srcs = ["NetworkLayer.h"],
    hdrs = ["Neuron.h"],
)

cc_library(
    name = "networkLayer",
    srcs = ["Network.h"],
    hdrs = ["Util.h"],
    deps = [
        "//tensorflow/cc:cc_ops",
        "//tensorflow/cc:client_session",
        "//tensorflow/core:tensorflow",
        ":neuron"],
)

cc_library(
    name = "network",
    srcs = ["ann.cpp"],
    hdrs = ["Util.h"],
    deps = [":networkLayer"],
)