open Type;

let color hue k =>
  "hsl(" ^
  Common.string_of_float hue ^
  "," ^ Common.string_of_float (k *. 60.0 +. 20.0) ^ "%," ^ Common.string_of_float (k *. 60.0 +. 20.0) ^ "%)";

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
