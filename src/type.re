type point = {
  x: float,
  y: float
};

type polygon = list point;

type badge = {zones: list polygon};

type box = {
  max: point,
  min: point
};
