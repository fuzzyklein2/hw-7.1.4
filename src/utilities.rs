//! Define helper functions for Rust programs.

unsafe extern "C" {
    /// # Returns
    /// 
    /// Pointer to the `const String::c_str()` from the h27 module.
    fn get_program_name() -> *const std::ffi::c_char;
}

unsafe extern "C" {
    fn cleanup_log_files();
}

pub fn program_name() -> &'static str {
    unsafe {
        std::ffi::CStr::from_ptr(get_program_name())
            .to_str()
            .unwrap()
    }
}

pub fn rotate_log_files() {
    unsafe {
        cleanup_log_files();
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_program_name() {
        assert!(program_name().starts_with("peroxide"));
    }
    
}