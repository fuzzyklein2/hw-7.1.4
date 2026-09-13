use clap::Parser;
use dirs;
use env_logger;
use log::LevelFilter;
use std::io::Write;

mod constants;
mod getargs;
mod files;
mod logging;
mod utilities;

use constants::{ BASE_DIR, FOLDER_PICT };
use files::{ cwd, FileSystem, home, pwd };
use getargs::Args;
use logging::{ error, warn, info, debug, trace };
use utilities::program_name;

fn main() {
    let prog_name = program_name();
    let args = Args::parse();

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
    
    info(&format!("Running {prog_name}"));
    warn("This program is under construction!");
    debug(&format!("Debugging {prog_name}"));
    trace(&format!("Debugging {prog_name} even more"));
    // error("Danger, Will Robinson!");
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

    let file_system = FileSystem::new();    

    debug(&format!(r#"File System:
Configuration file: {}
Data file:          {}
Log file:           {}
"#, file_system.config_file.display(),
    file_system.data_file.display(),
    file_system.log_file.display()
));
}
