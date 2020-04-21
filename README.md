# sine_gen
An Arduino sine wave generator using interpolated lookup table as the direct digital synthesis (DDS) method. 
DDS waveform generators can easily output waveforms with mHz or better relative frequency control, as well ass precise phase control between multiple waveforms.
In this demo, it contains a single analog output, updated by hooking an update function to Due's internal timer callback list.

The interpolation design in this firmware is based on the [DDS waveform generation reference design](https://forums.ni.com/t5/Example-Code/DDS-Waveform-Generation-Reference-Design-for-LabVIEW-FPGA/ta-p/3996130?profile.language=en) for NI FPGA. 

## Usage
1. Use `sine.py` to generate a waveform template, since different frequency is controlled through sampling interval on the microcontroller, number of samples reflects how truthful the signal can be when sampled by a high-frequency clock.
   ```
   n_samples = 2048
   resolution = 12
   filename = 'sine.h'
   ```
   Modify `filename` to control the generated path. 
   By default, Due (SAM3X8E) only has 12-bit resolution for its internal DAC, therefore, `resolution` is fixed to 12 here.
   
   After running the Python script, you should have a `sine.h` placed in the same folder.

2. In the firmware file, 
   ```
   const uint32_t UPDATE_US = 100;
   const uint32_t SAMPLE_STEP = 4294600;
   ```
   control how the controller step through the lookup table.
   - `UPDATE_US` defines how often the controller should update its output, this update rate should follow the Nyquist sampling criterion to avoid signal aliasing.
   - `SAMPLE_STEP` controls how far the controller step through the tabel during each lookup, which essentially controls the generated signal frequency.
   
3. Open the Arudino IDE and compile-upload the program. In the beginning, serial output will print current value of `SAMPLE_STEP`, and later, analog output `DAC1` will start dumping the sine wave.
