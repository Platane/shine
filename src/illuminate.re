open Type;

let color hue => "hsl(" ^ string_of_int hue ^ ",60%,60%)";

let string_of_float2: float => string =
  fun f => f < 0.0001 && f > (-0.0001) ? "0" : string_of_float f ^ "0";

let color hue k =>
  "hsl(" ^
  string_of_float2 hue ^
  "," ^ string_of_float2 (k *. 60.0 +. 20.0) ^ "%," ^ string_of_float2 (k *. 60.0 +. 20.0) ^ "%)";

let computeColor: zone => point => string =
  fun {normal, center} lightSource => {
    let n = Point.sub lightSource center |> Point.normalize;
    let k = Point.dot n normal;
    color 126.0 ( k *. 0.5 +. 0.5)
  };

let computeDefaultZones: list string => list zone =
  fun paths => {
    let polygons = paths |> List.map Parse.svgPathToPolygon;
    let (worldCenter, _worldRadius) = Point.boundingCircle (List.flatten polygons);
    List.map2
      (
        fun polygon path => {
          let (center, _radius) = Point.boundingCircle polygon;
          let normal = Point.sub center worldCenter |> Point.normalize;
          {vertices: polygon, normal, center, path}
        }
      )
      polygons
      paths
  };
