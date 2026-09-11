use env_logger;
use log::{ trace, debug, error, info, warn };

mod utilities;
use utilities::program_name;

fn main() {
    let prog_name = program_name();
    env_logger::init();
    info!("Running {}", prog_name);
    warn!("This program is under construction!");
    debug!("Debugging {}", prog_name);
    trace!("Debugging {} even more", prog_name);
    error!("🛑  Danger, Will Robinson!");
}
