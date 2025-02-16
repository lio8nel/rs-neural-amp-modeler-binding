#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

use std::ffi::CString;

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

pub struct NeuralDsp {
    handle: *mut NAMDsp_t,
}

impl NeuralDsp {
    pub fn new(config_path: &str) -> Result<Self, nam_error_t> {
        let mut error = nam_error_t_NAM_SUCCESS;
        let config_path = CString::new(config_path).unwrap();

        unsafe {
            let handle = nam_get_dsp_from_file(config_path.as_ptr(), &mut error);

            if error != nam_error_t_NAM_SUCCESS {
                Err(error)
            } else {
                Ok(Self { handle })
            }
        }
    }

    pub fn prewarm(&mut self) {
        unsafe { nam_dsp_prewarm(self.handle) }
    }

    pub fn set_loudness(&mut self, value: f64) {
        unsafe { nam_dsp_set_loudness(self.handle, value) }
    }

    pub fn set_input_level(&mut self, value: f64) {
        unsafe { nam_dsp_set_input_level(self.handle, value) }
    }

    pub fn set_output_level(&mut self, value: f64) {
        unsafe { nam_dsp_set_output_level(self.handle, value) }
    }
}

impl Drop for NeuralDsp {
    fn drop(&mut self) {
        unsafe { nam_destroy_dsp(self.handle) }
    }
}
