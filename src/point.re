open Type;

let add: point => point => point = fun a b => {x: a.x +. b.x, y: a.y +. b.y};

let sub: point => point => point = fun a b => {x: a.x -. b.x, y: a.y -. b.y};

let dot: point => point => float = fun a b => a.x *. b.x +. a.y *. b.y;

let scale: point => float => point = fun a k => {x: a.x *. k, y: a.y *. k};

let length: point => float = fun a => dot a a |> sqrt;

let distance: point => point => float = fun a b => sub a b |> length;

let normalize: point => point =
  fun a =>
    switch (length a) {
    | 0.0 => {x: 0.0, y: 0.0}
    | l => scale a (1.0 /. l)
    };

let rec boundingBox (points: list point) :box =>
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

let expandBoundingBox : box => point => box = fun box m =>
  {
    max : add box.max ( scale m 0.5 ),
    min : sub box.min ( scale m 0.5 ),
  };

let rec sumPoints (points: list point) :point =>
  switch points {
  | [] => {x: 0.0, y: 0.0}
  | [p, ...rest] => add p (sumPoints rest)
  };

let computeBarycenter (points: list point) :point =>
  scale (sumPoints points) (1.0 /. float_of_int (List.length points));

let rec reduce: ('b => 'a => 'b) => 'b => list 'a => 'b =
  fun fn defaultValue list =>
    switch list {
    | [] => defaultValue
    | [first, ...rest] => fn (reduce fn defaultValue rest) first
    };

let boundingCircle: list point => (point, float) =
  fun points => {
    let box = boundingBox points;
    let center: point = {x: (box.min.x +. box.max.x) /. 2.0, y: (box.min.y +. box.max.y) /. 2.0};
    let radius: float = reduce (fun r p => max r (distance p center)) 0.0 points;
    (center, radius)
  };
