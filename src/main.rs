use nam::NeuralDsp;

fn main() {
    match NeuralDsp::new("NeuralAmpModelerCore/example_models/wavenet.nam") {
        Ok(mut dsp) => {
            dsp.prewarm();
            dsp.set_loudness(0.5);
            dsp.set_input_level(1.0);
            dsp.set_output_level(1.0);
        }
        Err(e) => eprintln!("Failed to create DSP with error: {:?}", e),
    }
}
