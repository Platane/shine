const stylePool = {
  canvas: require('../component/style/canvas.css'),
};

export const getClassName = (mod, className) =>
  (stylePool[mod] || {})[className] || '';
