const tabs = ['Լուծում', '3D վիզուալիզացիա', '2D գրաֆիկ', 'Իտերացիաների տեսք'];

function Slider({ label }: { label: string }) {
  return (
    <div className="slider">
      <span className="muted">{label}</span>
      <div className="range-row"><span>−0.5</span><span>0.5</span></div>
      <div className="track"><div className="fill" /></div>
    </div>
  );
}

export default function VizPanel() {
  return (
    <section className="panel">
      <div className="tabs">
        {tabs.map((t, i) => <span key={t} className={i === 0 ? 'tab active' : 'tab'}>{t}</span>)}
      </div>
      <div className="viz-head">
        <h3>3D վիզուալիզացիա</h3>
        <div className="segmented"><span className="seg active">3D</span><span className="seg">2D</span></div>
      </div>
      <div className="placeholder">3D մակերևույթ</div>
      <div className="sliders"><Slider label="x-ի միջակայք" /><Slider label="y-ի միջակայք" /></div>
      <h3 className="viz-head">2D գրաֆիկ (y = 0 ուղղությամբ)</h3>
      <div className="placeholder small">2D գրաֆիկ</div>
    </section>
  );
}