use std::env;
use std::io::Error;
use std::fs;
use std::path::PathBuf;

use crate::constants::FOLDER_PICT;
use crate::logging::error;

/// # Returns
/// 
/// `path` to the process working directory.
/// ⚠️ This is not the directory containing the executable or the source file.
pub fn cwd() -> Result<PathBuf, Error> {
    match std::env::current_dir() {
        Ok(path) => Ok(path),
        Err(e) => {
            error("Couldn't get current working directory: {e}");
            Err(e)
        }
    }
}

pub fn pwd() {
    println!("{}Current working directory: {}",FOLDER_PICT, cwd().expect("REASON").display());
}

pub fn home() -> Option<PathBuf> {
    match env::home_dir() {
        Some(path) => Some(path),
        None => {
            error("Impossible to get your home dir!"); None
        }
    }
}

// pub struct FileSystem {
//     CONFIG_FILE: &str,
//     DATA_FILE: &str,
//     LOGS_DIR: &str,
    
// }

/*
match std::env::current_dir() {
    Ok(path) => println!("Current directory: {}", path.display()),
    Err(e) => eprintln!("Couldn't get current directory: {e}"),
}
*/