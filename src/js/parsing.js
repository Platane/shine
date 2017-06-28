export const extractSvgPath = textElement => {
  const dom = document.createElement('div');

  dom.innerHTML = textElement;

  return Array.from(dom.querySelectorAll('path')).map(path =>
    path.getAttribute('d')
  );
};

export const readFileAsText = (event, callback) => {
  const rf = new FileReader();

  rf.onerror = err => {
    console.log(err);
    callback('');
  };
  rf.onload = () => callback(rf.result);

  rf.readAsText(event.dataTransfer.files[0]);
};

export const svgPathToPolygon = path => {
  const numbers = path
    .replace(/[mML]/g, ' ')
    .replace(/ +/g, ' ')
    .trim()
    .split(' ');

  return Array.from({ length: Math.floor(numbers.length / 2) }).map((_, i) => [
    +numbers[i * 2],
    +numbers[i * 2 + 1],
  ]);
};
