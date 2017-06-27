external readFileAsText : 'event => (string => unit) => unit = "window.readFileAsText" [@@bs.val];

external extractSvgPath : string => array string = "window.extractSvgPath" [@@bs.val];

external svgPathToPolygon : string => array Type.point = "window.svgPathToPolygon" [@@bs.val];

let svgToPolygons: string => list Type.polygon =
  fun text =>
    extractSvgPath text |> Array.to_list |>
    List.map (fun path => path |> svgPathToPolygon |> Array.to_list);
