use std::env;
use std::io::Error;
use std::fs;
use std::path::PathBuf;

use crate::constants::{ BASE_DIR, FOLDER_PICT };
use crate::logging::{ error, log_file_name };
use crate::utilities::program_name;

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

pub struct FileSystem {
    pub config_file: PathBuf,
    pub data_file: PathBuf,
    pub log_file: PathBuf,
    // config_file: dirs::config_dir().unwrap().join("peroxide/config.json"),
    // data_file: BASE_DIR.join(format!("data/{}.json", program_name())),
    // log_file: home().join(format!(".logs/{}"))
}

impl FileSystem {
    pub fn new() -> Self {
        let config_dir = dirs::config_dir().unwrap().join("peroxide");

        Self {
            config_file: config_dir.join("config.json"),
            data_file: BASE_DIR.join(format!("data/{}.json", program_name())),
            log_file: home().unwrap().join(format!(".logs/{}/{}",program_name(), log_file_name())),
        }
    }
}

/*
match std::env::current_dir() {
    Ok(path) => println!("Current directory: {}", path.display()),
    Err(e) => eprintln!("Couldn't get current directory: {e}"),
}
*/