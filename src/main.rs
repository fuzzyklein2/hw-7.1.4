use env_logger;

mod constants;
mod logging;
mod utilities;

use logging::{ error, warn, info, debug, trace };
use utilities::program_name;

fn main() {
    let prog_name = program_name();
    env_logger::init();
    info(&format!("Running {prog_name}"));
    warn("This program is under construction!");
    debug(&format!("Debugging {prog_name}"));
    trace(&format!("Debugging {prog_name} even more"));
    error("Danger, Will Robinson!");
}
