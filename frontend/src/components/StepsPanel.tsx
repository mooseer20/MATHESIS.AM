import { BookOpen, CheckCircle2, Repeat } from 'lucide-react';

const steps = [
  { title: 'Վերլուծել խնդիրը', text: 'Ուղիղ տեղադրումը տալիս է 0/0, ուստի անհրաժեշտ է այլ մեթոդ։' },
  { title: 'Ընտրել մեթոդը', text: 'Առաջարկվում է՝ ռացիոնալացում։ Արտահայտությունը պարունակում է քառակուսի արմատների տարբերություն։' },
  { title: 'Լուծել', text: 'Բազմապատկում ենք Լծորդով՝', formula: '2 / (√(1+x) + √(1−x))' },
  { title: 'Հաշվել սահմանը', formula: '2 / (1 + 1) = 1' },
  { title: 'Արդյունք', formula: 'lim x→0 (√(1+x) − √(1−x)) / x = 1', result: true },
];

export default function StepsPanel() {
  return (
    <aside className="panel steps">
      <h2>Լուծման քայլեր</h2>
      {steps.map((s, i) => (
        <div key={s.title} className="step">
          <span className="num">{i + 1}</span>
          <div>
            <h3>{s.title}</h3>
            {s.text && <p>{s.text}</p>}
            {s.formula && <div className={s.result ? 'formula result' : 'formula'}>{s.formula}</div>}
          </div>
        </div>
      ))}
      <div className="verified">
        <CheckCircle2 size={18} />
        <span>Ստուգված է՝ արդյունքը հաստատվել է մի քանի մեթոդներով (ռացիոնալացում, Լոպիտալի կանոն)։</span>
      </div>
      <div className="actions">
        <button className="btn primary"><Repeat size={16} />Ցույց տալ այլ մեթոդ</button>
        <button className="btn"><BookOpen size={16} />Դիտել բացատրությունը</button>
      </div>
    </aside>
  );
}