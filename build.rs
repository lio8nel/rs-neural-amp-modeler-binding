use std::env;
use std::path::PathBuf;

fn main() {
    // Rebuild if our build script or main source changes
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=src/nam_get_dsp_wrapper.h");
    println!("cargo:rerun-if-changed=src/nam_get_dsp_wrapper.cpp");

    cc::Build::new()
        .include("NeuralAmpModelerCore/Dependencies/eigen")
        .include("NeuralAmpModelerCore/Dependencies/nlohmann/")
        .include("NeuralAmpModelerCore/NAM/")
        .file("NeuralAmpModelerCore/NAM/activations.cpp")
        .file("NeuralAmpModelerCore/NAM/convnet.cpp")
        .file("NeuralAmpModelerCore/NAM/lstm.cpp")
        .file("NeuralAmpModelerCore/NAM/wavenet.cpp")
        .file("NeuralAmpModelerCore/NAM/get_dsp.cpp")
        .file("NeuralAmpModelerCore/NAM/dsp.cpp")
        .file("nam_get_dsp_wrapper.cpp")
        .std("c++17")
        .compile("nam_get_dsp_wrapper");

    // Link against C++ standard library
    if cfg!(target_os = "macos") {
        println!("cargo:rustc-link-lib=c++");
    } else {
        println!("cargo:rustc-link-lib=stdc++");
    }

    // Generate bindings
    let bindings = bindgen::Builder::default()
        .header("nam_get_dsp_wrapper.h")
        .clang_arg("-xc++")
        .clang_arg("-std=c++17")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .generate()
        .expect("Unable to generate bindings");

    //
    // Write bindings to file
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
