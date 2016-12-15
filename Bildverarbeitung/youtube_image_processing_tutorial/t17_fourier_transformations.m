clear all, close all,
% hadamard transformation, or sinusoidal patterns for
figure, imshow('t17_fourier_tf.png'); % fourier tf introduction
figure, imshow('t17_fourier_tf_examples.png'); 
%%
% figure, imshow('t17_fourier_tf_inbuild.png'); 
x = 2:7
y = fft(x)
