// use std::ffi::CStr;

mod utilities;
use utilities::program_name;

fn main() {
    println!("Running {}", program_name());
}
