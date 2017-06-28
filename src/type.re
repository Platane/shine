type point = {
  x: float,
  y: float
};

type polygon = list point;

type zone = {
  path: string,
  vertices: polygon,
  normal:point,
  center:point
};

type badge = {
  zones: list zone
};

type box = {
  max: point,
  min: point
};
