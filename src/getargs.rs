use clap::Parser;

#[derive(Parser)]
#[command(version)]
pub struct Args {
    /// Enable debug logging
    #[arg(short = 'd', long = "debug")]
    pub debug: bool,
    /// Enable verbose logging
    #[arg(short = 'v', long = "verbose")]
    pub verbose: bool,
    /// Enable warnings
    #[arg(short = 'w', long = "warn")]
    pub warnings: bool,
    /// Enable trace logging
    #[arg(short = 't', long = "trace")]
    pub trace: bool,
    /// Other arguments
    pub args: Vec<String>,
}