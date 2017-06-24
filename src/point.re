let add: Type.point => Type.point => Type.point = fun a b => {x: a.x +. b.x, y: a.y +. b.y};

let scale: Type.point => float => Type.point = fun a k => {x: a.x /. k, y: a.y /. k};

let rec boundingBox (points: list Type.point) :Type.box =>
  switch points {
  | [] => {max: {x: 0.0, y: 0.0}, min: {x: 0.0, y: 0.0}}
  | [p] => {max: p, min: p}
  | [p, ...rest] =>
    let previousBox = boundingBox rest;
    {
      max: {x: max previousBox.max.x p.x, y: max previousBox.max.y p.y},
      min: {x: min previousBox.min.x p.x, y: min previousBox.min.y p.y}
    }
  };

let rec sumPoints (points: list Type.point) :Type.point =>
  switch points {
  | [] => {x: 0.0, y: 0.0}
  | [p, ...rest] => add p (sumPoints rest)
  };

let computeBarycenter (points: list Type.point) :Type.point =>
  scale (sumPoints points) (1.0 /. float_of_int (List.length points));
