use nam::NeuralDsp;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn verify_nam_dsp_creation() {
        match NeuralDsp::new("NeuralAmpModelerCore/example_models/wavenet.nam") {
            Ok(mut dsp) => {
                dsp.prewarm();
                dsp.set_loudness(0.5);
                dsp.set_input_level(1.0);
                dsp.set_output_level(1.0);
                assert!(true);
            }
            Err(e) => assert!(false, "Failed to create DSP with error: {:?}", e),
        }
    }
}
