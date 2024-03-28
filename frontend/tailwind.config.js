/** @type {import('tailwindcss').Config} */
const colors = require('tailwindcss/colors');

export default {
  content: [
    "./src/**/*.{js,jsx,ts,tsx}",
  ],
  theme: {
    extend: {},
    screens: {
      'xs': '0px',
      'sm': '576px',
      'md': '768px',
      'lg': '992px',
      'xl': '1200px',
      'xxl': '1400px',
    },
    fontFamily: {
      'poppins-thin': ['Poppins Thin', 'sans-serif'],
      'poppins-extralight': ['Poppins Extra Light', 'sans-serif'],
      'poppins-light': ['Poppins Light', 'sans-serif'],
      'poppins-normal': ['Poppins Normal', 'sans-serif'],
      'poppins-medium': ['Poppins Medium', 'sans-serif'],
      'poppins-semibold': ['Poppins Semi-bold', 'sans-serif'],
      'poppins-bold': ['Poppins Bold', 'sans-serif'],
      'poppins-extrabold': ['Poppins Extra Bold', 'sans-serif'],
      'poppins-black': ['Poppins Black', 'sans-serif'],
    },
    colors: {
      gray: colors.gray,
      white: colors.white,
      blue: colors.blue,
      violet: colors.violet,
      black: colors.black,
     'lumen-text': '#121211',
     'lumen-background': '#f9f8f7',
     'lumen-primary': '#f78d40',
     'lumen-secondary': '#d6b9a425',
     'lumen-accent': '#d19b75',
    },
  },
  plugins: [],
}
