#include "nam_get_dsp_wrapper.h"
#include "get_dsp.h"
#include <memory>
#include <stdexcept>

// Wrapper structs to hold C++ objects
struct NAMDsp_t
{
  std::unique_ptr<nam::DSP> dsp;
};

struct NAMDspData_t
{
  nam::dspData data;
};

nam_dsp_data_handle_t nam_create_dsp_data(void)
{
  try
  {
    return new NAMDspData_t();
  }
  catch (...)
  {
    return nullptr;
  }
}

void nam_destroy_dsp_data(nam_dsp_data_handle_t handle)
{
  if (handle)
  {
    delete handle;
  }
}

nam_dsp_handle_t nam_get_dsp_from_file(const char* config_filename, nam_error_t* error)
{
  if (!config_filename || !error)
  {
    if (error)
      *error = NAM_ERROR_INVALID_ARCHITECTURE;
    return nullptr;
  }

  try
  {
    auto handle = new NAMDsp_t();
    handle->dsp = nam::get_dsp(std::filesystem::path(config_filename));
    *error = NAM_SUCCESS;
    return handle;
  }
  catch (const std::runtime_error& e)
  {
    *error = NAM_ERROR_FILE_NOT_FOUND;
  }
  catch (const std::invalid_argument& e)
  {
    *error = NAM_ERROR_INVALID_VERSION;
  }
  catch (...)
  {
    *error = NAM_ERROR_UNKNOWN;
  }
  return nullptr;
}

nam_dsp_handle_t nam_get_dsp_from_file_with_config(const char* config_filename, nam_dsp_data_handle_t config,
                                                   nam_error_t* error)
{
  if (!config_filename || !config || !error)
  {
    if (error)
      *error = NAM_ERROR_INVALID_ARCHITECTURE;
    return nullptr;
  }

  try
  {
    auto handle = new NAMDsp_t();
    handle->dsp = nam::get_dsp(std::filesystem::path(config_filename), config->data);
    *error = NAM_SUCCESS;
    return handle;
  }
  catch (const std::runtime_error& e)
  {
    *error = NAM_ERROR_FILE_NOT_FOUND;
  }
  catch (const std::invalid_argument& e)
  {
    *error = NAM_ERROR_INVALID_VERSION;
  }
  catch (...)
  {
    *error = NAM_ERROR_UNKNOWN;
  }
  return nullptr;
}

nam_dsp_handle_t nam_get_dsp_from_config(nam_dsp_data_handle_t config, nam_error_t* error)
{
  if (!config || !error)
  {
    if (error)
      *error = NAM_ERROR_INVALID_ARCHITECTURE;
    return nullptr;
  }

  try
  {
    auto handle = new NAMDsp_t();
    handle->dsp = nam::get_dsp(config->data);
    *error = NAM_SUCCESS;
    return handle;
  }
  catch (const std::runtime_error& e)
  {
    *error = NAM_ERROR_CORRUPTED_MODEL;
  }
  catch (const std::invalid_argument& e)
  {
    *error = NAM_ERROR_INVALID_VERSION;
  }
  catch (...)
  {
    *error = NAM_ERROR_UNKNOWN;
  }
  return nullptr;
}

void nam_destroy_dsp(nam_dsp_handle_t handle)
{
  if (handle)
  {
    delete handle;
  }
}

void nam_dsp_prewarm(nam_dsp_handle_t handle)
{
  if (handle && handle->dsp)
  {
    handle->dsp->prewarm();
  }
}

void nam_dsp_set_loudness(nam_dsp_handle_t handle, double value)
{
  if (handle && handle->dsp)
  {
    handle->dsp->SetLoudness(value);
  }
}

void nam_dsp_set_input_level(nam_dsp_handle_t handle, double value)
{
  if (handle && handle->dsp)
  {
    handle->dsp->SetInputLevel(value);
  }
}

void nam_dsp_set_output_level(nam_dsp_handle_t handle, double value)
{
  if (handle && handle->dsp)
  {
    handle->dsp->SetOutputLevel(value);
  }
}