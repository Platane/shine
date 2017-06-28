let component = ReasonReact.statelessComponent "DropZone";

let handleDrop setZones event _ _ => {
  /* prevent from opening the image */
  ReactEventRe.Synthetic.preventDefault event;
  Parse.readFileAsText event ( fun text => text |> Parse.extractSvgPath |> setZones )
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
