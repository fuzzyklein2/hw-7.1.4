unsafe extern "C" {
    pub fn get_program_name() -> *const std::ffi::c_char;
}

pub fn program_name() -> *const std::ffi::c_char {
    unsafe { get_program_name() }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_program_name() {
        let s = unsafe {
            CStr::from_ptr(program_name()).to_str().unwrap()
        };
        assert_eq!("peroxide", s);
    }
}