const stylePool = {
  app: require('../component/style/app.css'),
  canvas: require('../component/style/canvas.css'),
};

export const getClassName = (mod, className) =>
  (stylePool[mod] || {})[className] || '';
