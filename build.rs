fn main() {
    println!("cargo:rustc-link-search=native=build");
    println!("cargo:rustc-link-lib=static=hw7");
    println!("cargo:rustc-link-lib=dylib=spdlog");
    println!("cargo:rustc-link-lib=dylib=magic");
    println!("cargo:rustc-link-lib=dylib=stdc++");
}
