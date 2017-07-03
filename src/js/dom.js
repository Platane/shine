export const startDrag = (onMouseMove, onMouseUp) => {
  const root = window;

  const up = event => {
    onMouseUp(event);

    root.removeEventListener('mouseup', up);
    root.removeEventListener('mousemove', onMouseMove);
  };

  root.addEventListener('mouseup', up);
  root.addEventListener('mousemove', onMouseMove);
};
