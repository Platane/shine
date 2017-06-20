external readFileAsText : 'event => (string => 'whatever) => 'whatever =
  "window.readFileAsText" [@@bs.val];

let parseSvg: string => list Type.polygon =
  fun text => [[{x: 0.0, y: 0.0}, {x: 2.0, y: 5.0}, {x: 10.0, y: 2.0}]];

let component = ReasonReact.statelessComponent "DropZone";

let handleDrop setZones event _ _ => {
  /* prevent from opening the image */
  ReactEventRe.Synthetic.preventDefault event;
  readFileAsText event (fun text => setZones (parseSvg text))
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
