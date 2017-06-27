type point = {
  x: float,
  y: float
};

type polygon = list point;

type zone = { vertices: polygon, normal:point };

type badge = {
  zones: list zone
};

type box = {
  max: point,
  min: point
};
