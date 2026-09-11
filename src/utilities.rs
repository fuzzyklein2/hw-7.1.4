
unsafe extern "C" {
    fn get_program_name() -> *const std::ffi::c_char;
}

pub fn program_name() -> &'static str {
    unsafe {
        std::ffi::CStr::from_ptr(get_program_name())
            .to_str()
            .unwrap()
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