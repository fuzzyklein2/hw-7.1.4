use chrono::Local;

use crate::constants::{ ERROR_PICT, WARN_PICT, INFO_PICT, DEBUG_PICT, TRACE_PICT, CHECK_PICT, FAILURE_PICT };

pub fn error(s: &str) {
    log::error!("{ERROR_PICT}{s}");
}

pub fn warn(s: &str) {
    log::warn!("{WARN_PICT}{s}");
}

pub fn info(s: &str) {
    log::info!("{INFO_PICT}{s}");
}

pub fn debug(s: &str) {
    log::debug!("{DEBUG_PICT}{s}");
}

pub fn trace(s: &str) {
    log::trace!("{TRACE_PICT}{s}");
}

pub fn log_file_name() -> String {
    format!("{}.log", Local::now().format("%Y%m%d_%H:%M:%S"))
}