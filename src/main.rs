use clap::Parser;
use dirs;
use env_logger;
use json::JsonValue;
use log::LevelFilter;
use std::io::{ Error, Write };
use std::sync::OnceLock;

mod config;
mod constants;
mod getargs;
mod files;
mod logging;
mod utilities;

use config::JSON;
use constants::{ BASE_DIR, FOLDER_PICT };
use files::{ cwd, FileSystem, home, pwd };
use getargs::{ Args, get_piped_input };
use logging::{ error, warn, info, debug, trace, init_log };
use utilities::program_name;

static FILE_SYSTEM: OnceLock<FileSystem> = OnceLock::new();
static CONFIGURATION: OnceLock<JSON> = OnceLock::new();
static PROGRAM_DATA: OnceLock<JSON> = OnceLock::new();
static INPUT: OnceLock<String> = OnceLock::new();

fn main() -> Result<(), Error> {
    let prog_name = program_name();
    let args = Args::parse();
    FILE_SYSTEM.set(FileSystem::new()).unwrap();
    CONFIGURATION.set(JSON::new(&FILE_SYSTEM.get().unwrap().config_file)).unwrap();
    PROGRAM_DATA.set(JSON::new(&FILE_SYSTEM.get().unwrap().data_file)).unwrap();
    
    if let Some(input) = get_piped_input() {
        INPUT.set(input).unwrap();
    }
    
    let level = if args.trace {
        LevelFilter::Trace
    } else if args.debug {
        LevelFilter::Debug
    } else if args.verbose {
        LevelFilter::Info
    } else if args.warnings {
        LevelFilter::Warn
    } else {
        LevelFilter::Error
    };
    
    // env_logger::init();
    env_logger::Builder::new().filter_level(level).format(|buf, record| {
        writeln!(buf, "{} {}", record.level(), record.args())
    }).init();
    
    init_log()?;

    info(&format!("Running {prog_name}"));
    warn("This program is under construction!");
    debug(&format!("Debugging {prog_name}"));
    trace(&format!("Debugging {prog_name} even more"));
    error("Danger, Will Robinson!");
    // pwd();
    let s = cwd().unwrap();
    debug(&format!("Current working directory: {}", s.display()));
    let s = BASE_DIR.display();
    debug(&format!("Base directory: {s}"));
    let home = home().unwrap();
    debug(&format!("User home directory: {}", home.display()));
    debug(&format!("Arguments: {:#?}", args.args));

// `xdg` directories
trace(&format!(r#"
XDG Directories:
----------------
Audio:                 {}
Cache:                 {}
Configuration:         {}
Local Configuration:   {}
Data:                  {}
Local Data:            {}
Desktop:               {}
Documents:             {}
Downloads:             {}
Executables:           {}
Fonts:                 {}
Home:                  {}
Pictures:              {}
Preferences:           {}
Public:                {}
Runtime:               {}
State:                 {}
Templates:             {}
Videos:                {}
"#, dirs::audio_dir().unwrap().display(),
    dirs::cache_dir().unwrap().display(),
    dirs::config_dir().unwrap().display(),
    dirs::config_local_dir().unwrap().display(),
    dirs::data_dir().unwrap().display(),
    dirs::data_local_dir().unwrap().display(),
    dirs::desktop_dir().unwrap().display(),
    dirs::document_dir().unwrap().display(),
    dirs::download_dir().unwrap().display(),
    dirs::executable_dir().unwrap().display(),
    dirs::font_dir().unwrap().display(),
    dirs::home_dir().unwrap().display(),
    dirs::picture_dir().unwrap().display(),
    dirs::preference_dir().unwrap().display(),
    dirs::public_dir().unwrap().display(),
    dirs::runtime_dir().unwrap().display(),
    dirs::state_dir().unwrap().display(),
    dirs::template_dir().unwrap().display(),
    dirs::video_dir().unwrap().display(),
));

    debug(&format!(r#"File System:
Configuration file: {}
Data file:          {}
Log file:           {}
"#, FILE_SYSTEM.get().unwrap().config_file.display(),
    FILE_SYSTEM.get().unwrap().data_file.display(),
    FILE_SYSTEM.get().unwrap().log_file.display()
));

    debug(&format!(r#"Configuration:
{}
"#, json::stringify_pretty(CONFIGURATION.get().unwrap().value.clone(), 4)
));
    
    debug(&format!(r#"Program Data:
{}
"#, json::stringify_pretty(PROGRAM_DATA.get().unwrap().value.clone(), 4)
));

    if let Some(input) = INPUT.get() {
    debug(&format!(r#"Piped Input:
{}
"#, input
));
    }
    
    Ok(())
}
