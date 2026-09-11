use std::ffi::CStr;

mod utilities;
// use utilities::get_program_name;

fn main() {
    let prog_name = unsafe {
        CStr::from_ptr(utilities::program_name()).to_string_lossy()
    };
    println!("Running {prog_name}");
}
