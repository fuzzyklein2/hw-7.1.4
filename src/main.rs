use clap::Parser;
use env_logger;
use log::LevelFilter;

mod constants;
mod getargs;
mod files;
mod logging;
mod utilities;

use constants::{ BASE_DIR, FOLDER_PICT };
use files::{ cwd, home, pwd };
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
    env_logger::Builder::new().filter_level(level).init();
    
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
}
