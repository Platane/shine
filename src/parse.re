external readFileAsText : 'event => (string => unit) => unit = "window.readFileAsText" [@@bs.val];

external extractSvgPath_ : string => array string = "window.extractSvgPath" [@@bs.val];

external svgPathToPolygon_ : string => array Type.point = "window.svgPathToPolygon" [@@bs.val];

let extractSvgPath x => extractSvgPath_ x |> Array.to_list;

let svgPathToPolygon x => svgPathToPolygon_ x |> Array.to_list;