use std::fs

/// # Returns
/// 
/// `path` to the process working directory.
/// ⚠️ This is not the directory containing the executable or the source file.
pub fn cwd() -> const fs::path {
    
}

/*
match std::env::current_dir() {
    Ok(path) => println!("Current directory: {}", path.display()),
    Err(e) => eprintln!("Couldn't get current directory: {e}"),
}
*/