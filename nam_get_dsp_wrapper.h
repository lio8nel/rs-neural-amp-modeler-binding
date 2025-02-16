#ifndef NAM_GET_DSP_WRAPPER_H
#define NAM_GET_DSP_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointer types
typedef struct NAMDsp_t* nam_dsp_handle_t;
typedef struct NAMDspData_t* nam_dsp_data_handle_t;

// Error codes
typedef enum
{
  NAM_SUCCESS = 0,
  NAM_ERROR_FILE_NOT_FOUND = -1,
  NAM_ERROR_INVALID_VERSION = -2,
  NAM_ERROR_CORRUPTED_MODEL = -3,
  NAM_ERROR_INVALID_ARCHITECTURE = -4,
  NAM_ERROR_MEMORY = -5,
  NAM_ERROR_UNKNOWN = -99
} nam_error_t;

// Create and destroy DSP data handle
nam_dsp_data_handle_t nam_create_dsp_data(void);
void nam_destroy_dsp_data(nam_dsp_data_handle_t handle);

// Main functions
nam_dsp_handle_t nam_get_dsp_from_file(const char* config_filename, nam_error_t* error);
nam_dsp_handle_t nam_get_dsp_from_file_with_config(const char* config_filename, nam_dsp_data_handle_t config,
                                                   nam_error_t* error);
nam_dsp_handle_t nam_get_dsp_from_config(nam_dsp_data_handle_t config, nam_error_t* error);

// Cleanup
void nam_destroy_dsp(nam_dsp_handle_t handle);

// DSP operations
void nam_dsp_prewarm(nam_dsp_handle_t handle);
void nam_dsp_set_loudness(nam_dsp_handle_t handle, double value);
void nam_dsp_set_input_level(nam_dsp_handle_t handle, double value);
void nam_dsp_set_output_level(nam_dsp_handle_t handle, double value);

#ifdef __cplusplus
}
#endif

#endif // NAM_GET_DSP_WRAPPER_H