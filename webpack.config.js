const path = require('path');
const webpack = require('webpack');
const ExtractTextPlugin = require('extract-text-webpack-plugin');

const production = 'production' === process.env.NODE_ENV;

module.exports = {
  entry: {
    index: ['./src/js/index.js', './lib/js/src/app.js', './src/index.html'],
  },

  output: {
    path: path.join(__dirname, 'dist'),
    filename: '[name].js',
  },

  module: {
    rules: [
      {
        test: /\.js$/,
        use: [
          {
            loader: 'babel-loader',
          },
        ],
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
        test: /\.css$/,
        use: ExtractTextPlugin.extract({
          use: [
            {
              loader: 'css-loader',
              options: {
                modules: true,
                importLoaders: true,
                localIdentName: production
                  ? '[hash:8]'
                  : '[path][name]---[local]',
              },
            },
          ],
        }),
      },
    ],
  },

  devServer: {
    port: 8082,
    contentBase: [path.join(__dirname, 'src/asset')],
    watchOptions: {
      ignored: /node_modules/,
    },
  },

  plugins: [
    new webpack.DefinePlugin({
      // env var
      ['process.env.NODE_ENV']: `'${process.env.NODE_ENV}'`,
    }),

    new ExtractTextPlugin({ filename: 'style.css', allChunks: true }),

    new webpack.NamedModulesPlugin(),

    new webpack.optimize.ModuleConcatenationPlugin(),

    production &&
      new webpack.optimize.UglifyJsPlugin({
        sourceMap: false,
        comments: false,
      }),
  ].filter(Boolean),

  devtool: 'source-map',
};
