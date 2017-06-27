open Type;

let color hue => "hsl(" ^ string_of_int hue ^ ",60%,60%)";

let string_of_float2: float => string =
  fun f => f < 0.0001 && f > (-0.0001) ? "0" : string_of_float f ^ "0";

let color hue k =>
  "hsl(" ^
  string_of_float2 hue ^
  "," ^ string_of_float2 (k *. 60.0 +. 20.0) ^ "%," ^ string_of_float2 (k *. 60.0 +. 20.0) ^ "%)";

let computeColor: zone => point => string =
  fun {normal, vertices} lightSource => {
    let (center, _radius) = Point.boundingCircle vertices;
    let n = Point.sub lightSource center |> Point.normalize;
    let k = Point.dot n normal;
    color 126.0 (k *. 0.5 +. 0.5)
  };

let computeDefaultZones: list polygon => list zone =
  fun polygons => {
    let (worldCenter, _radius) = Point.boundingCircle (List.flatten polygons);
    List.map
      (
        fun polygon => {
          let (center, _radius) = Point.boundingCircle polygon;
          let normal = Point.sub worldCenter center |> Point.normalize;
          {vertices: polygon, normal}
        }
      )
      polygons
  };
