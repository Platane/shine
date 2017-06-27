const path = require('path');
const webpack = require('webpack');

const production = 'production' == process.env.NODE_ENV;

module.exports = {
  entry: {
    index: ['./lib/js/src/app.js', './src/index.html'],
    elk: ['./src/asset/elk.svg'],
    ball: ['./src/asset/ball.svg'],
  },

  output: {
    path: path.join(__dirname, 'dist'),
    filename: '[name].js',
  },

  module: {
    rules: [
      {
        test: /\.js$/,
        use: [],
      },

      {
        test: /\.html$/,
        use: [
          {
            loader: 'file-loader',
            options: {
              name: '[name].[ext]',
            },
          },
        ],
      },
      {
        test: /\.svg$/,
        use: [
          {
            loader: 'file-loader',
            options: {
              name: '[name].[ext]',
            },
          },
        ],
      },
    ],
  },

  plugins: [
    new webpack.DefinePlugin({
      // env var
      ['process.env.NODE_ENV']: `'${process.env.NODE_ENV}'`,
    }),
  ],

  devtool: 'source-map',
};
