external readFileAsText : 'event => (string => unit) => unit = "window.readFileAsText" [@@bs.val];

external extractSvgPath : string => array string = "window.extractSvgPath" [@@bs.val];

external svgPathToPolygon : string => array Type.point = "window.svgPathToPolygon" [@@bs.val];

let component = ReasonReact.statelessComponent "DropZone";

let handleDrop setZones event _ _ => {
  /* prevent from opening the image */
  ReactEventRe.Synthetic.preventDefault event;
  readFileAsText
    event
    (
      fun text => {
        let paths = extractSvgPath text;
        let polygons =
          List.map (fun path => svgPathToPolygon path |> Array.to_list) (Array.to_list paths);
        setZones polygons
      }
    )
};

let handleDragOver event _ _ => ReactEventRe.Synthetic.preventDefault event;

let make ::setZones _children => {
  ...component,
  render: fun () self =>
    <div
      style=(
        ReactDOMRe.Style.make
          position::"relative" width::"100px" height::"100px" boxShadow::"0 0 10px 0 black" ()
      )
      onDragOver=(self.handle handleDragOver)
      onDrop=(self.handle (handleDrop setZones))
    />
};
